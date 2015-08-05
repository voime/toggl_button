#!/usr/bin/python

file_project = '/root/toggl_button/project.json'
file_time = '/root/toggl_button/time_id.txt'

fApi = open('/root/toggl_button/api_key.txt','r')
api_key = fApi.read()
# TODO need fix this function
# if attribute tags exist then write tags
# this function converts json to dictonary and only wid, pid, tags and description keys
def toProject( result ):
	project = {}
	#print result2
	
	#if hasattr(result, 'wid'):
	project["wid"]=result["wid"]
	#if hasattr(result, 'pid'):
	project["pid"]=result["pid"]
	#if hasattr(result, 'description'):
	project["description"]=result["description"]
	#if hasattr(result, 'tags'):
	#	project["tags"]=result["tags"]
	project["created_with"]='curl'
	return project
