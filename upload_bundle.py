#!/opt/local/bin/python

import boto
from boto.s3.key import Key
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-v", "--version", dest="version", help="Bundle Version")
parser.add_option("-k", "--key", dest="key", help="Amazon Access Key")
parser.add_option("-s", "--secret", dest="secret", help="Amazon Secret Access Key")

(options, args) = parser.parse_args()

conn = boto.connect_s3(options.key, options.secret)

bucket_name = 'lookio-cdn'
bucket = conn.get_bucket(bucket_name)

filename = "bundle.zip"
k = Key(bucket)
k.key = "ios/" + options.version + "/" + filename
k.set_contents_from_filename(filename)
k.set_metadata('Cache-Control', 'max-age=15, must-revalidate');
k.set_acl('public-read')

