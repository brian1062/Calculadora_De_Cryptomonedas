import requests
import time

FIFO_NAME  = "/tmp/fifo_crypto"

headers = {
        'X-CMC_PRO_API_KEY': 'c34b5ad5-c1ab-4952-9805-38eca2a5ccc3',
        'Accepts': 'application/json'
        }

params = {
        'start': '1',
        'limit': '1',
        'convert': 'USD'
        }
#USD, ARS, EUR

url = 'https://pro-api.coinmarketcap.com/v1/cryptocurrency/listings/latest'

json = requests.get(url, params = params, headers = headers).json()

coins =  json['data']

#TIENEN QUE SER VALORES COMO 'ETH', 'BTC'
def get_currency_price (currency):
    for coin in coins:
        if coin['symbol'] == currency:
            return str(round(coin['quote']['USD']['price'],2))

precio = get_currency_price('BTC')
print(precio)
precio = get_currency_price('ETH')
print(precio)
