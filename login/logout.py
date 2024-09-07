import argparse
import requests

url = 'http://192.0.0.6/cgi-bin/force_logout'

parser = argparse.ArgumentParser(description='读取用户名和密码')
parser.add_argument('-u', '--username', required=True, help='用户名')
parser.add_argument('-p', '--password', required=True, help='密码')

args = parser.parse_args()

username = args.username
password = args.password

headers = {
    'Accept': '*/*',
    'Accept-Language': 'en-US,en;q=0.9',
    'Connection': 'keep-alive',
    'Content-Type': 'application/x-www-form-urlencoded',
    'Cookie': 'PHPSESSID=7943a8b9370461ffe5387baeaf5d3577',
    'Origin': 'http://192.0.0.6',
    'Referer': 'http://192.0.0.6/',
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0.0.0 Safari/537.36'
}

data = {
    'username': username,
    'password': password,
    'drop': '0',
    'type': '1',
    'n': '1'
}

response = requests.post(url, headers=headers, data=data, verify=False)

print(response.text)
