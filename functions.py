#!/bin/env python

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
	return project
