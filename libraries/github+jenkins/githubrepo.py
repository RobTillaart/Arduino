import datetime
import sys
from github import GitHubRepo
import jenkins
import logging

logging.captureWarnings(True)

# REPOS = [ (GH-ORG, GH-REPO, JENKINS-TOKEN, [(GH-MILESTONE, JENKINS-JOB)*] ]
REPOS = [
    ('RobTillaart', 'Arduino', 'JB',
        [
            ('MS', 'JJ'),
            (None, 'JJ')
        ]
     ),
    ]


def main():
    '''
    PR-poller fetches PR's from GitHub.com
    and starts them on Jenkins if needed
    '''
    if len(sys.argv) != 1:
        print 'usage: python ' + sys.argv[0]
        sys.exit(1)

    print '\nStart:\t{}'.format(datetime.datetime.now())

    for (org, repo, token, milestones) in REPOS:
        github = 'https://api.github.com/repos/'
        user = ''
        passwd = ''
        with GitHubRepo(github, user, passwd, org, repo) as ghr:
            # header
            print
            print 'CHECKING:\t' + ghr.url
            print 'PRs FOUND:\t' + str(len(ghr.pullRequests))
            print '--------------------------------------------------'
            print 'PR\tCOMMITS\tACTION\tSTATE\tMILESTONE'
            print '--------------------------------------------------'

            count = {}
            for pr in ghr.pullRequests:
                action = 'skip'
                state = ghr.get_status(pr.sha)
                if pr.wip:
                    state = 'WIP'
                    pass
                elif len(state) > 0:
                    state = state[0]['state']
                    pass
                else:
                    for (ms, job) in milestones:
                        state = 'ms error'
                        if pr.milestone == ms:
                            state = 'scheduled'
                            action = 'start'
                            jenkins.start_job(job, token, pr.sha)
                            repo.update_status(pr.sha, 'pending', job)
                            break

                if state in count:
                    count[state] = count[state] + 1
                else:
                    count[state] = 1

                print \
                    str(pr.number) + '\t' + \
                    ghr.get_commits_count(pr.number) + '\t' + \
                    action + '\t' + \
                    state + '\t' + \
                    pr.milestone + '\t' + \
                    pr.title

            # footer
            print '--------------------------------------------------'
            for key, value in sorted(count.items()):
                print '{0:<14}'.format(key) + '\t' + str(value)
            print '\nStop:\t{}\n'.format(datetime.datetime.now())


if __name__ == '__main__':
    main()
