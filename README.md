# BlackBerry Dynamics SDK for iOS

## Resources

Resources for developing application using BlackBerry Dynamics are located here:
[https://developers.blackberry.com/us/en/resources](https://developers.blackberry.com/us/en/resources)

These include:
### API Reference

The BlackBerry Dynamics SDK API Reference can be viewed online by selecting __API Reference__.

### Getting started guide

For a step by step guide to integrating your new or existing iOS applications with BlackBerry Dynamics select __Getting Started__.

## Support

To collaborate with other developers or to provide feedback to BlackBerry use the __BlackBerry Beta Community__ within the support area of the developer website.

## Updating for new releases

Create a new branch named `feature/{{ new version }}. Update the URLs and hashes for each framework. Create a release on this branch where the tag is `pre-{{ new version }}` with the framework zip files attached. The `pre-` part of the tag name is important because it prevents SPM from resolving that tag as the next version. This release should NOT be marked as latest.

Once the PR is merged, create a new release where the tag is the appropriate version number and should be marked as latest.

*&copy; 2022 BlackBerry Limited. All rights reserved.*
