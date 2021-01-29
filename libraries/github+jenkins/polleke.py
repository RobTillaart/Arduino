# -----------------------------------------------------------------------------
# Name:        poll_pull_request.py
# Purpose:
#
# Author:      rob.van.den.tillaart@fei.com
#
# Created:     18-03-2014
# Copyright:   (c) FEI 2014-2015
# Licence:     <your licence>
# -----------------------------------------------------------------------------

import datetime
import json
import requests
from requests.auth import HTTPBasicAuth
import sys

# REPOS = [ (GH-ORG, GH-REPO, JENKINS-TOKEN, [(GH-MILESTONE, JENKINS-JOB)*] ]
REPOS = [
    ('Aap', 'B', 'JB',
        [
            ('MS', 'JJ')
        ]
     ),
]

GITHUB = 'https://api.github.com/repos/'
GH_USER = 'user'
GH_PASSWD = 'passwd'
JENKINS = 'http://jenkins/jenkins/job/'

class GitHub:
    """
    Github class interfaces with github.com to fetch information about
    PR's and setting the status of PR's
    """
    def __init__(self):
        """ initializes the class with static info
        """
        self.base_url = GITHUB
        self.user = GH_USER
        self.password = GH_PASSWD
        self.authentication = HTTPBasicAuth(self.user, self.password)

    def set_repo(self, org, repo):
        self.org = org + "/"
        self.repo = repo + "/"
        self.url = self.base_url + self.org + self.repo
        self.pr_url = self.base_url + self.org + self.repo + "pull/"

    def get_url(self, url):
        response = requests.get(
            url=url,
            auth=self.authentication,
            verify=False
            )
        return response.json()

    def get_open_pull_request(self):
        """ gets a list of open PR's from github.com
        """
        url = self.url + "pulls?state=open&per_page=100"
        return self.get_url(url)

    def get_status(self, sha):
        """ gets status of a PR from github.com
        """
        url = self.url + "statuses/{}".format(sha)
        return self.get_url(url)

    def get_commits(self, num):
        """ gets commits of a PR from github.com
        """
        url = self.url + "pulls/{number}/commits".format(number=num)
        return self.get_url(url)

    def update_status(self, sha, state, prtestjob, buildnr=None):
        """ updates status of PR in github.com
        """
        url = self.url + "statuses/{}".format(sha)

        if state == 'success':
            description = "The build succeeded!"
        elif state == 'failure':
            description = "The build failed!"
        elif state == 'error':
            description = "The build has errors!"
        elif state == 'pending':
            description = "The build is pending!"
        else:
            return "invalid state: " + state

        jenkins_url = self.base_url + prtestjob + "/"
        if buildnr is not None:
            jenkins_url = jenkins_url + buildnr + "/consoleFull"

        update = {
            "state": state,
            "target_url": jenkins_url,
            "description": description
            }

        response = requests.post(
            url=url,
            data=json.dumps(update),
            auth=self.authentication,
            verify=False
            )
        if response.ok is False:
            print "network error"
        return response.json()


class Jenkins:
    """
    Jenkins class is used to start jobs on Jenkins.
    """
    def __init__(self):
        self.base_url = JENKINS

    def start_job(self, job, token, sha):
        """ Schedules PR test job in Jenkins
        """
        url = self.base_url + job + "/buildWithParameters?" + \
            "token={token}&git_branch={branch}" \
            .format(token=token, branch=sha)
        response = requests.get(url=url)
        return response.ok


def main():
    """
    PR-poller fetches PR's from GitHub.com
    and starts them on Jenkins if needed
    """
    if len(sys.argv) != 1:
        print "usage: python " + sys.argv[0]
        sys.exit(1)

    print '\nStart:\t{}\n'.format(datetime.datetime.now())

    github = GitHub()
    jenkins = Jenkins()

    for (org, repo, token, milestones) in REPOS:
        github.set_repo(org, repo)

        pr_collection = github.get_open_pull_request()
        print
        print 'CHECKING:\t' + github.url
        print 'PRs FOUND:\t' + str(len(pr_collection))
        print '--------------------------------------------------'
        print 'PR\tCOMMITS\tACTION\tSTATE\tMILESTONE'
        print '--------------------------------------------------'

        count = {}

        for pull_request in pr_collection:
            prnr = pull_request['number']
            sha = pull_request['head']['sha']
            # print sha
            pr_state = github.get_status(sha)
            action = "-"
            milestone = "-"
            if pull_request['milestone'] is not None:
                milestone = pull_request['milestone'].get('title')

            commits = str(len(github.get_commits(prnr)))

            # SKIP IF WORK IN PROGRESS (WIP)
            if pull_request['title'].find('WIP') >= 0:
                state = 'WIP'
                action = 'SKIP'

            # SKIP IF ALLREADY RUNNING
            elif len(pr_state) != 0:
                state = pr_state[0]['state']
                action = 'SKIP'

            # ELSE ==> SCHEDULE
            else:
                # default it is error
                state = 'INVALID MILESTONE!'
                action = '---'
                for (ms, job) in milestones:
                    if milestone == ms:
                        jenkins.start_job(job, token, sha)
                        state = 'scheduled'
                        action = 'START'
                        github.update_status(sha, 'pending', job)

            print str(prnr) + '\t' + commits + '\t' + action + '\t' + \
                state + '\t' + milestone + '\t' + pull_request['title']

            if state in count:
                count[state] = count[state] + 1
            else:
                count[state] = 1

        print '--------------------------------------------------'
        for key, value in sorted(count.items()):
            print '{0:<14}'.format(key) + ' : ' + str(value)
        print 'time:\t{}\n'.format(datetime.datetime.now())


if __name__ == '__main__':
    main()