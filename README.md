## Developers

- Nikolaos Grigoroudis, csd4619@csd.uoc.gr
- Alexandros Christinakis, csd4764@csd.uoc.gr

## Notes per phase

### Phase I

- The project was implemented according to the project guidelines
- Things that were not implemented: None

## Build

Requirements:
- `CMake` (minimum version 3.18.4)
- `Flex` (tested on version 2.6.4)
- `gcc`

### al

Target `al` of cmake

Alternatively, if `bash` is installed:
- Command: `bash compile.sh`
- Output: `build/al`

## For Developers

### Git and Gitlab

#### Git User Credentials
Before the first commit, you should configure (locally most likely) your:
- `user.name` the **same** as in Gitlab
- `user.email` the **same** as in Gitlab

Example:
- `git config user.name "JOHN DOE"`
- `git config user.email "csdXXXX@csd.uoc.gr"`

> Note, that in csd's Gitlab, the email **must** be your university email.
> Also, your name (which is your full name and not a nick name), by default,
> should contain only capital letters.

#### Branch Naming
All letters must be lowercase. If you want to write multiple words in a field,
then you should separate them with `_` (underscore).

The name of a branch should have the following format:

- `<short-name>/<kind>-<issue-number>/<scope>-<description>`
    - `short-name`: Your short (nick)name
    - `kind`: [optional but highly recommended] What kind of branch it is
    - `issue-number`: [optional and \<kind\> must exist] The number of a related
issue
    - `scope`: The scope that refers to
    - `description`: A short description of the branch

Examples:
- `alex/fix-64/gui-enable_exit_button` // There is an issue (#64) in Gitlab
- `alex/fix/gui-enable_connect_button` // There is not an issue in Gitlab
- `nick/feat-32/gui-add_mute_button` // There is an issue (#32) in Gitlab
- `nick/feat/gui-add_mute_button` // There is not an issue in Gitlab

> These branches don't follow the above rules, but they are shared among
> developers:
> 1. main: The default (aka "stable") branch.
> 2. dev: The "unstable" branch (not sure if it is ready to be merged to main).
> 3. dev/\*: (\* is wildcard) Branch for feature that multiple developer works
> on it. In that case, each developer's branch is merged into this branch
> instead of main or dev. Note, that those branches must follow all of the above
> rules, excluding the \<short-name\> (in this case it's `dev`).

#### Commit Messages
1. Follow [conventional commits](https://www.conventionalcommits.org/en/v1.0.0/).
    - An unofficial, but more user friendly, guide can be found [here](https://gist.github.com/qoomon/5dfcdf8eec66a051ecd85625518cfd13).
2. Follow the 50/72 rule.
    - 50 is the maximum number of characters of the commit title.
    - 72 is the maximum character length of the commit body.
3. Always start with lowercase letters a scope.
    - In some cases, you can violate this, but only if you are *sure* about it.
4. Use camel case in scope.
5. Commit messages should be very clear about what their commits do.

#### Commit Structure
Each commit should add only one feature (or fix only one issue, etc). In case a
commit contains different changes, then you should brake it to more commits.

In other words, make a lot and small commits, where each commit contains closely
related changes.

#### Merge Requests
If a merge request is not ready to be merged, then it **must** be `Draft`.

Each merge request should be small and contain only one feature (or bug fix,
etc). All the changes that the merge request contains must be closely related.

The assignee of a merge request is the developer that is responsible about the
specific change (usually yourself or the developer who wrote the changes).

A merge request should me merged by the assignee when **all** the other
developers have approve it. If there are conflicts, again, assignee is
responsible to resolve them.

> Avoid using `rebase` for resolving conflicts.

In order to merge a merge request, all its threads must be resolved. A thread
should be closed only by the one who opened it.

If there is a related issue to the merge request, then you should link the merge
request with the issue (via `#<issue-id>`, where \<issue-id\> is the number of
the issue).

#### Remote Branches
You can force push to a branch, when it starts with your name (short-name) and:
there is no merge request (for this branch) or its merge request is `Draft`.

#### Protected Branches
Branches `main`, `dev` and `dev/*` (\* is wildcard) should be protected.

#### Issues and Labels
Every issue should have a label. If none of the existing labels describes the
issue, feel free to create a new one and set its color and priority.

Don't assign an issue to a developer, unless you are sure about it.

#### Tags
For each turn in, there must be a tag with the following format:
- name: `turnin-p<phase>-<tow-digit-turnin-no>`
- message: `Turned in by csd<XXXX>`

Example for Phase 1:
- name: `turnin-p1-01`
- message: `Turned in by csd4764`

Example for Phase 1 (3rd turn in):
- name: `turnin-p1-03`
- message: `Turned in by csd4764`

Example for Phase 3:
- name: `turnin-p3-01`
- message: `Turned in by csd4619`

> Always format the code before stage/commit.

### Code and Style
1. Format the code according to `.clang-format`.
2. Always use keyword `this` when accessing class' data or methods.
3. Always declare a method `const` when possible.
4. When casting, always use `*_cast<>()` template.
5. Use `override` keyword when overriding a virtual method
