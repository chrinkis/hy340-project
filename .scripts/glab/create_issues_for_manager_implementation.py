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

managers = [
    "forstmt",
    "stmt",
    "expr",
    "term",
    "assignexpr",
    "primary",
    "lvalue",
    "member",
    "call",
    "callsuffix",
    "normcall",
    "methodcall",
    "elist",
    "elist_opt",
    "objectdef",
    "indexed",
    "indexed_opt",
    "indexedelem",
    "block",
    "block_open",
    "block_body",
    "block_close",
    "funcdef",
    "funcprefix",
    "funcargs",
    "funcbody",
    "const",
    "idlist",
    "idlist_id",
    "idlist_opt",
    "ifstmt",
    "ifstmt_if",
    "ifstmt_else",
    "whilestmt",
    "whilestmt_whil",
    "whilestmt_cond",
    "forstmt",
    "forstmt_pre",
    "forstmt_n",
    "forstmt_m",
    "returnstmt",
    "stmts",
    "breakstmt",
    "continuestmt",
]

for manager in managers:
    issue = project.issues.create({
        "title": "Implement and use `" + manager + "` manager",
        "labels": ["bison", "todo", "syntax managers"],
        "milestone_id": 4,
    })
