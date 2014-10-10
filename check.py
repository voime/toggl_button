#!/usr/bin/python
import requests, json
from functions import *

url = "https://www.toggl.com/api/v8/time_entries/current"
r = requests.get(url, auth=(api_key, 'api_token'))
if r:
	result = r.json()
	#print result
	if result["data"]:
		with open(file_project, 'r') as projectFile:
			project = projectFile.read()
		
		project_array = json.loads(project)
		
		if result["data"]["pid"] == project_array["pid"]:
			with open(file_time, 'w') as timeFile:
					tid = result["data"]["id"]
					json.dump(tid, timeFile)
			# project is running
			print "1"
		else:
			# wrong prject running
			print "2"

	else:
		# project dont run
		print "2"

else:
	# no connection
	print "0"
