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
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-14.0.8198.22/BlackBerryCerticom.xcframework.zip",
            checksum: "58a5c8f15d3be9a214a28107178b2a823dc18866a5befdf7d6e67d5ba9033ebf"
        ),
        .binaryTarget(
            name: "BlackBerryCerticomSBGSE",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-14.0.8198.22/BlackBerryCerticomSBGSE.xcframework.zip",
            checksum: "1f51a48bf620a74d5920417c555cb163a794d62cd8daec4b3933952cde35bcab"
        ),
        .binaryTarget(
            name: "BlackBerryDynamics",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-14.0.8198.22/BlackBerryDynamics.xcframework.zip",
            checksum: "d88478a3d3ebbbae7549796698f2d75acd168070189df4acc91b684e735d2fbe"
        ),
        .binaryTarget(
            name: "BlackBerryDynamicsAutomatedTestSupportLibrary",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-14.0.8198.22/BlackBerryDynamicsAutomatedTestSupportLibrary.xcframework.zip",
            checksum: "e4b65e22952ec75b817ac23fd03d312461a9743220a31e6e8f985a9ccf4b5a2f"
        ),
    ]
)
