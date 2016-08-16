[![ZenHub](https://raw.githubusercontent.com/ZenHubIO/support/master/zenhub-badge.png)](https://raw.githubusercontent.com/ZenHubIO/support/master/zenhub-badge.png)

# Version Control
This repository has adopted the [git flow branching model](http://nvie.com/posts/a-successful-git-branching-model/).
The creators of git flow released a [short intro video](http://vimeo.com/16018419) to explain the model.

The `master` branch is production-ready and contains the latest tagged releases.
Before a release is made, it is stagged in `release/x` branches before being pushed
and tagged in the `master` branch. Small patches from `hotfix/x` branches are also
pushed to `master`, and will always have a release version.
The `develop` branch is pre-production, and is where we push `feature/x` branches for testing.

Most modern git clients support git flow. If you are however using the git CLI
on *nix, please install the git flow plugin on your distribution.

# General Description
This module represents the code that will run on each of the "worker nodes"
of the project. These nodes are responsible for pull jobs from a Messaging
Queue. Then decoding these jobs to get the code that should be benchmarked.
Then executing the code and doing the desired benchmarkig and finally placing
the result of the benchmark back onto the Queue.

The system is built using the Cmake tool. This choice was infulenced by the fact
that the development team is using the CLion IDE which requires Cmake to be used.

In terms of assistance in setting up the app in general, one can refer to the 
Installation Manual. In depth documentation for the project as a whole including
this module can be found in the service-documentation repository which is located
here: https://github.com/CodingInfinity/Benchmark-Service-Documentation

##For more information please read the wiki
https://github.com/CodingInfinity/Benchmark-Service-Documentation/wiki

# Sponsorships
## ZenHub 

<a href="https://zenhub.com"><img src="https://raw.githubusercontent.com/ZenHubIO/support/master/zenhub-badge.png"></a>

**ZenHub is how the world's best development teams work together.** ? 

As the only project management tool integrated natively in GitHub's UI, ZenHub helps you stay in your workflow without distractions. There are no new queues to check, entries to update, or priorities to manage outside GitHub. 

Because ZenHub's features are powered by native GitHub issues, it doesn't create more process - it gets out of your way so you can focus on shipping awesome products.

Download the ZenHub extension for Firefox or Chrome [here](http://www.zenhub.com). It's free for public, academic, and personal repositories. 
