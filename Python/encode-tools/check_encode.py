#! /usr/bin/Python
# -*- coding: UTF-8 -*- 
import chardet
import sys, os
import codecs

def CheckEncode(filename):
	suffixlists = ['.h', '.cpp', '.c']
	suffix = os.path.splitext(filename)[1]

	if suffix not in suffixlists:
		return None

	with open(filename, 'rb') as fp:
		content = fp.read()
		adchar = chardet.detect(content)
		return adchar['encoding']

# def InputFileCheck():
# 	'''
# 		check the file of Encoding
# 	'''
# 	if len(sys.argv) <= 1:
# 		print "Please Input the file"
# 	filename = sys.argv[1]
# 	if not os.path.exists(filename):
# 		print "The file is not exits"
# 	ret = CheckEncode(filename)

if __name__ == '__main__':
	
	startdir = os.path.join(os.path.dirname(__file__), '../..')
	basedir = os.path.abspath(startdir)
	# included = ['ascii', 'GB2312']
	charsets = ['UTF-16LE', 'UTF-16BE', 'UTF-8-SIG', 'utf-8']
	first = True
	new_charset = 'gb2312'

	for root, subdirs, files in os.walk(basedir):
		for filepath in files:
			fullpath = os.path.join(root, filepath)
			old_charset = CheckEncode(fullpath) 
			if old_charset and old_charset in charsets:
				if first:
					print "File type warning:"
					first = False
				print "    %s is encoded with %s."%(fullpath, old_charset)
