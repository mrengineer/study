import sqlite3
import os
import csv
import io
import time
import threading
import matplotlib.pyplot as plt
from flask import Flask, request, jsonify
import telebot
from telebot import types
from dotenv import load_dotenv

load_dotenv()

TOKEN = os.getenv('TELEGRAM_TOKEN')
admin_chat_id = int(os.getenv('ADMIN_CHAT_ID'))
DATABASE_PATH = os.environ.get('DB_PATH', '/data/devices.db')

app = Flask(__name__)
bot = telebot.TeleBot(TOKEN)

def init_db():
    conn = sqlite3.connect(DATABASE_PATH)
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS devices (
                        id TEXT PRIMARY KEY,
                        last_seen TIMESTAMP
                    )''')
    cursor.execute('''CREATE TABLE IF NOT EXISTS data (
                        id TEXT,
                        date TIMESTAMP,
                        value INTEGER
                    )''')
    cursor.execute('''CREATE TABLE IF NOT EXISTS commands (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        device_id TEXT,
                        command TEXT,
                        status TEXT,
                        result TEXT
                    )''')
    cursor.execute('''CREATE TABLE IF NOT EXISTS heartbeat (
                        id TEXT,
                        timestamp REAL,
                        temperature REAL
                    )''')
    conn.commit()
    conn.close()

init_db()

# ============ HTTP API =================
@app.route('/register', methods=['POST'])
def register():
    device_id = request.form.get('id')
    if not device_id:
        return 'Missing ID', 400
    conn = sqlite3.connect(DATABASE_PATH)
    conn.execute('INSERT OR IGNORE INTO devices (id, last_seen) VALUES (?, ?)', (device_id, time.time()))
    conn.commit()
    conn.close()
    return 'Registered', 200

@app.route('/data', methods=['POST'])
def upload_data():
    device_id = request.form.get('id')
    if 'file' not in request.files:
        return 'No file', 400
    f = request.files['file']
    content = io.StringIO(f.stream.read().decode("utf-8"))
    reader = csv.reader(content)
    conn = sqlite3.connect(DATABASE_PATH)
    for row in reader:
        conn.execute('INSERT INTO data (id, date, value) VALUES (?, ?, ?)', (device_id, row[0], row[1]))
    conn.commit()
    conn.close()
    return 'Data received', 200

@app.route('/heartbeat', methods=['POST'])
def heartbeat():
    device_id = request.form.get('id')
    temperature = request.form.get('temperature', type=float)
    timestamp = time.time()
    conn = sqlite3.connect(DATABASE_PATH)
    cursor = conn.cursor()
    cursor.execute('UPDATE devices SET last_seen = ? WHERE id = ?', (timestamp, device_id))
    cursor.execute('INSERT INTO heartbeat (id, timestamp, temperature) VALUES (?, ?, ?)', (device_id, timestamp, temperature))
    # Удаляем старые записи
    cursor.execute('''DELETE FROM heartbeat 
                      WHERE rowid NOT IN (
                          SELECT rowid FROM heartbeat WHERE id=? ORDER BY timestamp DESC LIMIT 1000
                      ) AND id=?''', (device_id, device_id))
    cursor.execute('SELECT id, command FROM commands WHERE device_id=? AND status="ожидание" ORDER BY id ASC LIMIT 1', (device_id,))
    row = cursor.fetchone()
    if row:
        command_id, command_text = row
        cursor.execute('UPDATE commands SET status="доставлена" WHERE id=?', (command_id,))
        notify_user(f'Команда {command_id} для {device_id} доставлена')
    else:
        command_id, command_text = None, ''
    conn.commit()
    conn.close()
    return jsonify({'id': command_id, 'command': command_text})

@app.route('/command_result', methods=['POST'])
def command_result():
    command_id = request.form.get('command_id')
    result = request.form.get('result')
    conn = sqlite3.connect(DATABASE_PATH)
    conn.execute('UPDATE commands SET result=?, status="выполнена" WHERE id=?', (result, command_id))
    conn.commit()
    conn.close()
    notify_user(f'Команда {command_id} выполнена. Результат: {result}')
    return 'OK', 200

# ============ Telegram BOT =================

def notify_user(text):
    bot.send_message(admin_chat_id, text)

@bot.message_handler(commands=['start'])
def handle_start(msg):
    bot.send_message(msg.chat.id, "Добро пожаловать! Команды выведутся по /help или начните набирать /")

@bot.message_handler(commands=['help'])
def handle_help(msg):
    help_text = (
        "Доступные команды:\n"
        "/devices — список устройств и время последней связи\n"
        "/status ID — статус устройства, график температуры\n"
        "/del_device ID — удалить устройство и все его данные\n"
        "/send_cmd ID команда — отправить команду устройству\n"
        "/del_cmd ID — удалить команду по ID\n"
        "/help — показать эту справку"
    )
    bot.send_message(msg.chat.id, help_text)

@bot.message_handler(commands=['devices'])
def list_devices(msg):
    conn = sqlite3.connect(DATABASE_PATH)
    rows = conn.execute('SELECT id, last_seen FROM devices').fetchall()
    conn.close()
    response = '\n'.join([f'{row[0]} — последний контакт: {time.ctime(row[1])}' for row in rows])
    bot.send_message(msg.chat.id, response or 'Нет устройств')

@bot.message_handler(commands=['status'])
def device_status(msg):
    try:
        _, device_id = msg.text.split()
    except:
        bot.send_message(msg.chat.id, 'Формат: /status ID')
        return
    conn = sqlite3.connect(DATABASE_PATH)
    last_seen = conn.execute('SELECT last_seen FROM devices WHERE id=?', (device_id,)).fetchone()
    data_count = conn.execute('SELECT COUNT(*) FROM data WHERE id=?', (device_id,)).fetchone()[0]
    latest_temp = conn.execute('SELECT temperature FROM heartbeat WHERE id=? ORDER BY timestamp DESC LIMIT 1', (device_id,)).fetchone()
    heartbeat_rows = conn.execute('SELECT timestamp, temperature FROM heartbeat WHERE id=? ORDER BY timestamp DESC LIMIT 1000', (device_id,)).fetchall()
    conn.close()

    if not last_seen:
        bot.send_message(msg.chat.id, 'Устройство не найдено')
        return

    response = f"Последняя связь: {time.ctime(last_seen[0])}\n"
    response += f"Записей: {data_count}\n"
    response += f"Температура: {latest_temp[0] if latest_temp else 'нет данных'} °C"
    bot.send_message(msg.chat.id, response)

    if heartbeat_rows:
        heartbeat_rows.reverse()
        x = [time.strftime('%H:%M:%S', time.localtime(ts)) for i, (ts, _) in enumerate(heartbeat_rows) if i % 10 == 0]
        y = [temp for i, (_, temp) in enumerate(heartbeat_rows) if i % 10 == 0]
        plt.figure(figsize=(10, 4))
        plt.plot(x, y, marker='o')
        plt.xticks(rotation=45)
        plt.title(f"Температура устройства {device_id}")
        plt.ylabel("°C")
        plt.tight_layout()
        img_path = f'/tmp/{device_id}_temp.png'
        plt.savefig(img_path)
        plt.close()
        with open(img_path, 'rb') as f:
            bot.send_photo(msg.chat.id, f)

@bot.message_handler(commands=['del_device'])
def delete_device(msg):
    try:
        _, device_id = msg.text.split()
    except:
        bot.send_message(msg.chat.id, 'Формат: /del_device ID')
        return
    conn = sqlite3.connect(DATABASE_PATH)
    conn.execute('DELETE FROM devices WHERE id=?', (device_id,))
    conn.execute('DELETE FROM data WHERE id=?', (device_id,))
    conn.execute('DELETE FROM commands WHERE device_id=?', (device_id,))
    conn.execute('DELETE FROM heartbeat WHERE id=?', (device_id,))
    conn.commit()
    conn.close()
    bot.send_message(msg.chat.id, f'Устройство {device_id} удалено')

@bot.message_handler(commands=['send_cmd'])
def send_cmd(msg):
    try:
        _, device_id, *cmd_parts = msg.text.split()
        cmd = ' '.join(cmd_parts)
    except:
        bot.send_message(msg.chat.id, 'Формат: /send_cmd ID команда')
        return
    conn = sqlite3.connect(DATABASE_PATH)
    conn.execute('INSERT INTO commands (device_id, command, status) VALUES (?, ?, ?)', (device_id, cmd, 'ожидание'))
    conn.commit()
    conn.close()
    bot.send_message(msg.chat.id, 'Команда добавлена')

@bot.message_handler(commands=['del_cmd'])
def del_cmd(msg):
    try:
        _, cmd_id = msg.text.split()
    except:
        bot.send_message(msg.chat.id, 'Формат: /del_cmd ID')
        return
    conn = sqlite3.connect(DATABASE_PATH)
    conn.execute('DELETE FROM commands WHERE id=?', (cmd_id,))
    conn.commit()
    conn.close()
    bot.send_message(msg.chat.id, 'Команда удалена')

@bot.message_handler(func=lambda message: True)
def debug_chat_id(message):
    bot.send_message(message.chat.id, f"Ваш chat_id: {message.chat.id}")

# ============ Start Threads =================
threading.Thread(target=lambda: bot.polling(none_stop=True)).start()

if __name__ == '__main__':
    commands = [
        types.BotCommand("start", "Старт бота"),
        types.BotCommand("help", "Справка по командам"),
        types.BotCommand("devices", "Список устройств"),
        types.BotCommand("status", "Статус устройства"),
        types.BotCommand("del_device", "Удалить устройство"),
        types.BotCommand("send_cmd", "Отправить команду устройству"),
        types.BotCommand("del_cmd", "Удалить команду"),
    ]
    bot.set_my_commands(commands)
    app.run(host='0.0.0.0', port=5000)
