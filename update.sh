#!/bin/bash

# Определяем директорию скрипта, чтобы найти ключ рядом с ним
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Имя файла ключа (лежит в той же директории, что и скрипт)
KEY_FILE="id_rsa"   # <-- Замените, если ваш ключ называется иначе

# Путь до ключа
KEY_PATH="$SCRIPT_DIR/$KEY_FILE"

# Настройки (пропишите свои пути/пользователя/хост)
LOCAL_DIR="/path/to/local/dir"
REMOTE_USER="user"
REMOTE_HOST="host"
REMOTE_DIR="/path/to/remote/dir"

# Параметры для ssh и scp, чтобы использовать ключ из той же папки
SSH_OPTS="-i \"$KEY_PATH\" -o StrictHostKeyChecking=no"
SCP_OPTS="-i \"$KEY_PATH\" -o StrictHostKeyChecking=no"

# Флаг: стал ли хотя бы один файл обновлённым
UPDATED=0

# =================================================================
# Рекурсивный обход: find "$LOCAL_DIR" -type f
# – найдёт все файлы во всех вложенных директориях внутри LOCAL_DIR.
# =================================================================
while read -r LOCAL_FILE; do
    # Вычисляем относительный путь (например, если LOCAL_DIR=/home/pi/files
    # и LOCAL_FILE=/home/pi/files/docs/report.txt, то REL_PATH=docs/report.txt)
    REL_PATH="${LOCAL_FILE#$LOCAL_DIR/}"
    REMOTE_FILE="$REMOTE_DIR/$REL_PATH"

    # Атрибуты локального файла
    LOCAL_MTIME=$(stat -c %Y "$LOCAL_FILE")
    LOCAL_SIZE=$(stat -c %s "$LOCAL_FILE")

    # Пытаемся получить атрибуты удалённого (mtime и размер) через SSH
    REMOTE_STAT=$(ssh $SSH_OPTS "$REMOTE_USER@$REMOTE_HOST" \
        "stat -c '%Y %s' '$REMOTE_FILE'" 2>/dev/null)

    if [[ -n "$REMOTE_STAT" ]]; then
        REMOTE_MTIME=$(echo "$REMOTE_STAT" | awk '{print $1}')
        REMOTE_SIZE=$(echo "$REMOTE_STAT" | awk '{print $2}')

        # Если хоть mtime, хоть размер отличается — скачиваем
        if [[ "$REMOTE_MTIME" -ne "$LOCAL_MTIME" || "$REMOTE_SIZE" -ne "$LOCAL_SIZE" ]]; then
            echo "Обновляется: $REL_PATH"
            # mkdir -p создаст вложенные папки, если их ещё нет
            mkdir -p "$(dirname "$LOCAL_FILE")"
            scp $SCP_OPTS "$REMOTE_USER@$REMOTE_HOST:$REMOTE_FILE" "$LOCAL_FILE"
            UPDATED=1
        fi
    fi
done < <(find "$LOCAL_DIR" -type f)

# Проверяем, был ли хоть один обновлённый файл
if [[ "$UPDATED" -eq 1 ]]; then
    echo
    echo "Обнаружены и скачаны обновлённые файлы."
    # Запросим подтверждение только в этом случае
    while true; do
        read -p "Подтвердите завершение работы скрипта (y/n): " answer
        case "$answer" in
            [Yy]* )
                echo "Подтверждено. Скрипт завершён."
                break
                ;;
            [Nn]* )
                echo "Подтверждение не получено. Скрипт остановлен."
                exit 1
                ;;
            * )
                echo "Пожалуйста, введите y (да) или n (нет)."
                ;;
        esac
    done
else
    echo
    echo "Обновлений файлов не обнаружено."
fi
