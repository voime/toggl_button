#!/usr/bin/python

import requests, json
from functions import *

requests.packages.urllib3.disable_warnings()

url = "https://www.toggl.com/api/v8/time_entries/current"
r = requests.get(url, auth=(api_key, 'api_token'))

if r:
	result = r.json()
	data = result.get("data")
	#print result
	if data:
		# save project info
		with open(file_project, 'w') as projectFile:
			json.dump(toProject(data), projectFile)
		# save time id
		with open(file_time, 'w') as timeFile:
			tid = data.get("id")
			json.dump(tid, timeFile)
			# print tid
			print "1"
	else:
		#  project dont run
		print "2"
else:
	# no connection
	print "0"


