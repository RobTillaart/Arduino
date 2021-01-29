import json
import requests
from requests.auth import HTTPBasicAuth


class GitHubRepo(object):

    def __init__(self, githubURL, user, passwd, organisation, repository):
        ''' initializes the class with static info
        '''
        self.base_url = githubURL
        if user is None or user is '':
            self.authentication = None
        else:
            self.authentication = HTTPBasicAuth(user, passwd)
        self.url = self.base_url + organisation + '/' + repository + '/'
        self.pr_url = self.url + 'pull/'

    def __enter__(self):
        return self

    def __exit__(self, exctype, excinst, exctb):
        pass

    def get_url(self, url):
        response = requests.get(
            url=url,
            auth=self.authentication,
            verify=False
            )
        return response.json()

    @property
    def pullRequests(self):
        url = self.url + 'pulls?state=open&per_page=100'
        return pullRequests(self.get_url(url))

    def get_commits_count(self, num):
        url = self.url + 'pulls/{number}/commits'.format(number=num)
        return str(len(self.get_url(url)))

    def get_status(self, sha):
        ''' gets status of a PR from github.com
        '''
        url = self.url + 'statuses/{}'.format(sha)
        state = self.get_url(url)
        if state is None:
            return 'xxx'
        return state

    def update_status(self, sha, state, prtestjob, buildnr=None):
        ''' updates status of PR in github.com
        '''
        url = self.url + 'statuses/{}'.format(sha)

        if state == 'success':
            description = 'The build succeeded!'
        elif state == 'failure':
            description = 'The build failed!'
        elif state == 'error':
            description = 'The build has errors!'
        elif state == 'pending':
            description = 'The build is pending!'
        else:
            return 'invalid state: ' + state

        jenkins_url = self.base_url + prtestjob + '/'
        if buildnr is not None:
            jenkins_url = jenkins_url + buildnr + '/consoleFull'

        update = {
            'state': state,
            'target_url': jenkins_url,
            'description': description
            }

        response = requests.post(
            url=url,
            data=json.dumps(update),
            auth=self.authentication,
            verify=False
            )
        if response.ok is False:
            print 'network error'
        return response.json()


class pullRequests(object):

    def __init__(self, prs):
        self.prs = prs

    def __len__(self):
        return len(self.prs)

    def __getitem__(self, index):
        if index >= len(self):
            raise IndexError
        return pullRequest(self.prs[index])


class pullRequest(object):

    def __init__(self, pullrequest):
        # print pullrequest
        self.pr = pullrequest

    @property
    def number(self):
        return self.pr['number']

    @property
    def title(self):
        return self.pr['title']

    @property
    def wip(self):
        return self.pr['title'].find('WIP') >= 0

    @property
    def sha(self):
        return self.pr['head']['sha']

    @property
    def date(self):
        return self.pr['head']['repo']['updated_at']

    @property
    def milestone(self):
        if self.pr['milestone'] is not None:
            return str(self.pr['milestone']['title'])
        return '-'

    @property
    def action(self):
        return '---'
