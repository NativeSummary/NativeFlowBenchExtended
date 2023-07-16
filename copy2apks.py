
import os
import shutil

file_prefix = ['build','outputs','apk','release']
file_name_template = '{}-release-unsigned.apk'

for file in os.listdir('.'):
    if not os.path.isdir(file):
        continue
    if not file.startswith('native_'):
        continue
    apk_name = file_name_template.format(file)
    coms = [file]+file_prefix+[apk_name]
    path = os.path.join(*coms)
    if os.path.exists(path):
        print(path)
        shutil.move(path, os.path.join('apks', apk_name))

# scp -r ./apks gpu:~/ns/dataset/nfbe