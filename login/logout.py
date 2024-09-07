import argparse
import urllib
import urllib.request as urllib2
import hashlib

class Logout:
    def __init__(self, username, password):  
        self.logout_url  = "http://192.0.0.6/cgi-bin/force_logout"
        self.headers = {}
        self.headers["User-Agent"] = "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.159 Safari/537.36"
        self.headers["Content-Type"] = "text/html; charset=gb2312"

        self.username = username
        password_md5 = hashlib.md5(password.encode('utf-8')).hexdigest()[8:24]
        self.password = password_md5


    def logout(self):
        data = {'username': self.username, 'password': self.password, "drop": 0, "type": 1, "n": 1}
        data = urllib.parse.urlencode(data).encode(encoding='UTF8')
        req = urllib2.Request(self.logout_url, data=data, headers=self.headers)
        res = urllib2.urlopen(req)
        content = res.read().decode('UTF8')
        return content



def main():
    parser = argparse.ArgumentParser(description='读取用户名和密码')
    parser.add_argument('-u', '--username', required=True, help='用户名')
    parser.add_argument('-p', '--password', required=True, help='密码')

    args = parser.parse_args()

    username = args.username
    password = args.password

    print(Logout(username, password))
    

if __name__ == "__main__":
    main()
