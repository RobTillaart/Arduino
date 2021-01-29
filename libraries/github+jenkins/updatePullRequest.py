import datetime
import sys
from github import GitHubRepo


def main():
    if ((len(sys.argv) != 6) and (len(sys.argv) != 7)):
        print 'usage: '
        # print sys.argv[0]+' /origin/pr/number/head state prtestjob [buildnr]'
        print sys.argv[0] + ' org repo sha state prtestjob [buildnr]'
        print 'org = RobTillaart'
        print 'repo = Arduino'
        print 'state = success | failure | error | pending'
        print 'number = github PullRequestNumber'
        print 'prtestjob = Jenkins job'
        print 'buildnr = jenkins buildNumber [optional]'
        return 1

    print '\nStart:\t{}'.format(datetime.datetime.now())

    # PARSE ARGUMENTS
    org = sys.argv[1]
    repo = sys.argv[2]
    sha = sys.argv[3]
    state = sys.argv[4]
    prtestjob = sys.argv[5]
    buildnr = '-'
    if (len(sys.argv) == 7):
        buildnr = sys.argv[6]

    # PROCESS
    github = 'https://api.github.com/repos/'
    user = ''
    passwd = ''
    with GitHubRepo(github, user, passwd, org, repo) as ghr:
        for pr in ghr.pullRequests:
            if pr.sha is sha:
                # PRINT INFO FOR LOGGING
                print '------------------------------'
                print 'PRURL:\t' + ghr.pr_url + str(pr.number)
                print 'TITLE:\t' + pr.title
                print 'STATE:\t' + state
                print 'BUILD:\t' + buildnr
                print 'SHA:\t' + sha

                # UPDATE PULL REQUEST STATUS
                ans = ghr.update_status(sha, state, prtestjob, buildnr)
                if ans is False:
                    print 'failed to update state'
                break

    # DONE
    print '\nStop:\t{}\n'.format(datetime.datetime.now())

if __name__ == '__main__':
    main()
