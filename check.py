#!/bin/env python
import requests, json
from pprint import pprint
from functions import *

fApi = open('api_key.txt','r')
api_key = fApi.read()

url = "https://www.toggl.com/api/v8/time_entries/current"
r = requests.get(url, auth=(api_key, 'api_token'))
if r:
	result = r.json()
	#print result
	if result["data"]:
		current_project = toProject( result["data"] )
		# vaja vaadata kas projekt on sama mis salvestatud

		with open('project.json', 'r') as projectFile:
			project = projectFile.read()

		pprint(json.dumps(current_project))
		pprint(project)

		if json.dumps(current_project) == project:
			# salvestan uue time ID
			with open('time_id.txt', 'w') as timeFile:
				tid = result["data"]["id"]
				json.dump(tid, timeFile)
				# print tid
				# project is running
				print "1"
		else:
			# wrong prject running
			print "0"
	else:
		# project dont run
		print "2"
else:
	# no connection
	print "0"
