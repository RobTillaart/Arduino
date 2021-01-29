import requests


class Jenkins:
    '''
    Jenkins class is used to start jobs on Jenkins.
    '''
    def __init__(self, jenkinsUrl):
        self.base_url = jenkinsUrl

    def start_job(self, job, token, sha):
        ''' Schedules PR test job in Jenkins
        '''
        return None
        url = self.base_url + job + '/buildWithParameters?' + \
            'token={token}&git_branch={branch}' \
            .format(token=token, branch=sha)
        response = requests.get(url=url)
        return response.ok
