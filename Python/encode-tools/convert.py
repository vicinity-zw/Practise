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

def change_file_charset(filepath, old_charset, new_charset):
	with open(filepath, 'r') as rf:
		file_offset = {'UTF-16LE': len(codecs.BOM_UTF16_LE), 'UTF-16BE': len(codecs.BOM_UTF16_BE)}
		utf_decode_map = {'UTF-16LE': 'utf_16_le', 'UTF-16BE': 'utf_16_be'}
		content = rf.read()

		try:
			if old_charset in file_offset.keys():
				decoder = codecs.getdecoder(utf_decode_map[old_charset])
				u_content = decoder(content[file_offset[old_charset]:])[0]
			else:
				u_content = content.decode(old_charset)
			newcontent = u_content.encode(new_charset)
		except UnicodeError:
			print "    %s can't be encoded with %s, please check the file."%(filepath, new_charset)
			return 			
		
		with open(filepath, 'w') as wf:
			wf.write(newcontent)
			print "    %s is encoded with %s"%(filepath, new_charset)


if __name__ == '__main__':

	startdir = os.path.join(os.path.dirname(__file__), '../..')
	basedir = os.path.abspath(startdir)
	# included = ['ascii', 'GB2312']
	charsets = ['UTF-16LE', 'UTF-16BE', 'UTF-8-SIG', 'utf-8']
	new_charset = 'gb2312'

	for root, subdirs, files in os.walk(basedir):
		for filepath in files:
			fullpath = os.path.join(root, filepath)
			old_charset = CheckEncode(fullpath) 
			if old_charset and old_charset in charsets:
				print "%s is encoded with %s."%(fullpath, old_charset) 
				change_file_charset(fullpath, old_charset, new_charset)
