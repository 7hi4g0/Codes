#!/usr/bin/env python
# -*- coding: utf-8 -*-
# python

import urllib, urllib2, cookielib
from bs4 import BeautifulSoup

data = {}
data['empresa'] = 'a665612'
data['matricula'] = '780'
data['senha'] = '780'
dados_feios = 'dados%5Bempresa%5D=a665612&dados%5Bmatricula%5D=780&dados%5Bsenha%5D=780'

cj = cookielib.CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
login_data = urllib.urlencode(data)
opener.open('http://www.ahgora.com.br/batidas/entrar/ajax', dados_feios)
page = opener.open('http://www.ahgora.com.br/batidas/ver')
html = page.read()
soup = BeautifulSoup(html)
print soup.find("div", { "class" : "float_r" })
