#!/bin/env python

import requests, json
from functions import *

fApi = open('api_key.txt','r')
api_key = fApi.read()

fTime = open('time_id.txt','r')
time_id = fTime.read()

# TODO need check if timeid is existing

url = "https://www.toggl.com/api/v8/time_entries/" + time_id + "/stop"

r = requests.put(url, auth=(api_key, 'api_token'))
print r.text

if r:
	result = r.json()
	if result["data"]:
		print "2"
	else:
		print "1"
else:
	print "0"
