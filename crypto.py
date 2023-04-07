import os
import requests
#import time


FIFO_NAME  = "/tmp/fifo_crypto"

headers = {
        'X-CMC_PRO_API_KEY': 'c34b5ad5-c1ab-4952-9805-38eca2a5ccc3',
        'Accepts': 'application/json'
        }

params = {
        'start': '1',
        'limit': '2',
        'convert': 'USD'
        }

#USD, ARS, EUR

URL = 'https://pro-api.coinmarketcap.com/v1/cryptocurrency/listings/latest'

json = requests.get(URL, params = params, headers = headers).json()

coins =  json['data']

#TIENEN QUE SER VALORES COMO 'ETH', 'BTC'
def get_currency_price (currency):
    for coin in coins:
        if coin['symbol'] == currency:
            return str(round(coin['quote']['USD']['price'],2))

PRECIO = get_currency_price('BTC')
print("Precio de Bitcoin", PRECIO)
PRECIO = get_currency_price('ETH')
print("Precio de Ethereum", PRECIO)

## ! FIFO

fifo = os.open(FIFO_NAME, os.O_RDWR)
PRICE = get_currency_price(os.read(fifo, 1024))
os.write(fifo, PRICE)