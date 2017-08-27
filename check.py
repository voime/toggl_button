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
		with open(file_project, 'r') as projectFile:
			project = projectFile.read()
		
		project_array = json.loads(project)
		
		if data.get("pid") == project_array.get("pid"):
			with open(file_time, 'w') as timeFile:
					tid = data.get("id")
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
