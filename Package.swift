// swift-tools-version:5.5

import PackageDescription

let package = Package(
name: "blackberry-dynamics-ios-sdk",
    platforms: [
        .iOS(.v15),
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
        .binaryTarget(name: "BlackBerryCerticom", path: "./Sources/BlackBerryCerticom.xcframework"),
        .binaryTarget(name: "BlackBerryCerticomSBGSE", path: "./Sources/BlackBerryCerticomSBGSE.xcframework"),
        .binaryTarget(name: "BlackBerryDynamics", path: "./Sources/BlackBerryDynamics.xcframework"),
        .binaryTarget(
            name: "BlackBerryDynamicsAutomatedTestSupportLibrary",
            path: "./Sources/BlackBerryDynamicsAutomatedTestSupportLibrary.xcframework"
        ),
    ]
)
