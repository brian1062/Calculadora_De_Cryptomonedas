import requests
import os

FIFO_NAME  = './fifo_crypto'

#Esta puesto el API KEY "OJO"
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
     
def parse_data(data):
    data = data.decode('utf-8')
    return data[:3]

## ! FIFO

fifo = os.open(FIFO_NAME, os.O_RDWR)
fifo_read= os.read(fifo, 16)
fifo_read = parse_data(fifo_read)
print(fifo_read)
PRICE = get_currency_price(fifo_read)
print(PRICE)
PRICE= PRICE.encode('utf-8')
os.write(fifo, PRICE)
#os.close(fifo)