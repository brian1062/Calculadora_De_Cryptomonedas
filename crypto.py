import requests
import os
import signal
import time

FIFO_NAME  = '/tmp/fifo_crypto'
FIFO_REQUEST = '/tmp/fifo_request'

# ! FIFO
if not os.path.exists(FIFO_NAME):
    os.mkfifo(FIFO_NAME)

fifo = os.open(FIFO_NAME, os.O_RDONLY)
# !

# ! Signal handling
def signal_handler(signal, frame):
    os.close(fifo)
    os.unlink(FIFO_NAME)
    print("\nThe SIGINT signal was received\n")
    exit(0)

signal.signal(signal.SIGINT, signal_handler)
# !

#Esta puesto el API KEY "OJO"
headers = {
        'X-CMC_PRO_API_KEY': 'c34b5ad5-c1ab-4952-9805-38eca2a5ccc3',
        'Accepts': 'application/json'
        }

params = {
        'start': '1',
        'limit': '10',
        'convert': 'USD'
        }
#USD, ARS, EUR

URL = 'https://pro-api.coinmarketcap.com/v1/cryptocurrency/listings/latest'

json = requests.get(URL, params = params, headers = headers).json()

coins = json['data']

#TIENEN QUE SER VALORES COMO 'ETH', 'BTC'
def get_currency_price (currency):
    for coin in coins:
        if coin['symbol'] == currency:
            return str(round(coin['quote']['USD']['price'],2))

def parse_data(data):
    data = data.decode('utf-8')
    null_index = data.find('\0')
    if null_index != -1:
        return data[:null_index]
    else:
        return data

# ! FIFO
fifo_read= os.read(fifo, 16)
fifo_read = parse_data(fifo_read)
print("Currency wanted:", fifo_read)
PRICE = get_currency_price(fifo_read)
print("Currency price:", PRICE)
PRICE= PRICE.encode('utf-8')
print("Price after encoding: ", PRICE)
os.close(fifo)
time.sleep(1)
os.open(FIFO_NAME, os.O_WRONLY)
os.write(fifo, PRICE)
#os.unlink(FIFO_NAME)
# !
