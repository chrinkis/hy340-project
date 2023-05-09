import gitlab
from getpass import getpass

# Personal token authentication
token = getpass("Give an access totken: ")

# Project Id
project_id = "7682"

gl = gitlab.Gitlab("https://gitlab-csd.datacenter.uoc.gr", private_token=token)

try:
    gl.auth()
except:
    print("Couldn't authenticate")
    exit(1)


project = gl.projects.get(project_id)

for i in range(117, 158):
    issue = project.issues.get(i)
    issue.due_date = "2023-05-10"
    issue.save()
