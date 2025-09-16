// swift-tools-version:5.9

import PackageDescription

let package = Package(
    name: "blackberry-dynamics-ios-sdk",
    platforms: [
        .iOS(.v17),
    ],
    products: [
        .library(name: "BlackBerryCerticom", targets: ["BlackBerryCerticom"]),
        .library(name: "BlackBerryCerticomSBGSE", targets: ["BlackBerryCerticomSBGSE"]),
        .library(name: "BlackBerryDynamics", targets: ["BlackBerryDynamics"]),
        .library(
            name: "BlackBerryDynamicsAutomatedTestSupportLibrary",
            targets: ["BlackBerryDynamicsAutomatedTestSupportLibrary"]
        ),
    ],
    targets: [
        .binaryTarget(
            name: "BlackBerryCerticom",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-14.0.8198-18/BlackBerryCerticom.xcframework.zip",
            checksum: "44624eb35ad6d9c78d060bf65bae468f8f8546a84fe17055f3c9d8688a2b124b"
        ),
        .binaryTarget(
            name: "BlackBerryCerticomSBGSE",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-14.0.8198-18/BlackBerryCerticomSBGSE.xcframework.zip",
            checksum: "3f321b56d1840c552b42c01b47e80f5b7e18ad6bf1b8f2b2023eacf77e56f975"
        ),
        .binaryTarget(
            name: "BlackBerryDynamics",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-14.0.8198-18/BlackBerryDynamics.xcframework.zip",
            checksum: "27cc02ddec6559fd7da6d1b6c88048506543a8112973a785d18c4f571bf809a7"
        ),
        .binaryTarget(
            name: "BlackBerryDynamicsAutomatedTestSupportLibrary",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-14.0.8198-18/BlackBerryDynamicsAutomatedTestSupportLibrary.xcframework.zip",
            checksum: "3db48bc21765a4b2b9a1e45c2d8896c78825dc3ceccedb9342ceb4c49ed9d9e7"
        ),
    ]
)
