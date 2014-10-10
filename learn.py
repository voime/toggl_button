#!/bin/env python

import requests, json
from functions import *

fApi = open('api_key.txt','r')
api_key = fApi.read()

url = "https://www.toggl.com/api/v8/time_entries/current"
r = requests.get(url, auth=(api_key, 'api_token'))
if r:
	result = r.json()
	#print result
	if result["data"]:
		project = toProject( result["data"] )
		# save project info
		with open('project.json', 'w') as projectFile:
			json.dump(project, projectFile)
		# save time id
		with open('time_id.txt', 'w') as timeFile:
			tid = result["data"]["id"]
			json.dump(tid, timeFile)
			# print tid
			print "1"
	else:
		#  project dont run
		print "2"
else:
	# no connection
	print "0"


