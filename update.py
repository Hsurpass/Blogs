#!/usr/bin/python3

import os
# import commands

res = {
    "Blogs": "git@github.com:Hsurpass/Blogs.git",
    # "ElegantTest": 'git@github.com:Hsurpass/ElegantTest.git',
    # 'houjie': 'git@github.com:Hsurpass/houjie.git',
    'log4js-demo': 'git@github.com:Hsurpass/log4js-demo.git',
    # 'mocha_integrative_test': 'git@github.com:Hsurpass/mocha_integrative_test.git',
    'plan': 'git@github.com:Hsurpass/plan.git',
    # 'wangguilin': 'git@github.com:Hsurpass/wangguilin.git',
    'winston_demo': 'git@github.com:Hsurpass/winston_demo.git'
}

def update_repository():
    for k,v in res.items():
        if os.path.exists(k):
            # print(os.path.exists('Blogs'))
            os.chdir(k)
            # print(os.path.abspath('.'))
            print('----------->Enter {0}'.format(k))

            os.system('git fetch')
            os.system('git rebase')
            # print("git update %s succ " % k)
            
            os.chdir('..')
            # print(os.path.abspath('.'))
            print("Leave {0}<------------".format(k))
        else:
            print('>>>>>>>>>>>>>>>start clone {0}'.format(k))
            os.system('git clone {0}'.format(v))
            print('finish clone {0}<<<<<<<<<<<<<<<<<<'.format(k))


if __name__ == "__main__":
    update_repository()