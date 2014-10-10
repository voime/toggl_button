#!/bin/env python
import requests, json
from pprint import pprint

fApi = open('api_key.txt','r')
api_key = fApi.read()

url = "https://www.toggl.com/api/v8/time_entries/start"
project_data = open('project.json')

# TODO need check if project exists

project = json.load(project_data)
data = {"time_entry":project}

#print json.dumps(data)
# start
r = requests.post(url, json.dumps(data), auth=(api_key, 'api_token'))
if r:
	result = r.json()
	#print result
	if result["data"]:
		tid = result["data"]["id"]
		print tid
		with open('time_id.txt', 'w') as timeFile:
			json.dump(tid, timeFile)
		
		#print project
		print "1"
	else:
		print "2"
else:
	print "0"


