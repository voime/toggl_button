#!/usr/bin/python
import requests, json
from functions import *

with open(file_project, 'r') as projectFile:
	project = projectFile.read()

# TODO need check if project exists
if project == "":
	# need learn new project
	print "5"
else:
	data = '{"time_entry":' + project + '}'

	url = "https://www.toggl.com/api/v8/time_entries/start"
	r = requests.post(url, data, auth=(api_key, 'api_token'))
	if r:
		result = r.json()
		#print result
		if result["data"]:
			tid = result["data"]["id"]
			#print tid
			with open(file_time, 'w') as timeFile:
				json.dump(tid, timeFile)
			
			#print project
			print "1"
		else:
			print "2"
	else:
		print "0"


