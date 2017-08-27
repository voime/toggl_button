#!/usr/bin/python
import requests, json
from functions import *

requests.packages.urllib3.disable_warnings()

fTime = open(file_time,'r')
time_id = fTime.read()

# TODO need check if timeid is existing
if time_id == "":
	print "1"
else:
	url = "https://www.toggl.com/api/v8/time_entries/" + time_id + "/stop"
	r = requests.put(url, auth=(api_key, 'api_token'))
	#print r.text
	if r:
		result = r.json()
		if result.get("data"):
			print "2"
		else:
			print "1"
	else:
		print "0"
