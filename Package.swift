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
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-13.1.0-48/BlackBerryCerticom.xcframework.zip",
            checksum: "4c0d930586fdbfeab6512f8bd129b3309a10ffadf6591be7ea0494e7fc701218"
        ),
        .binaryTarget(
            name: "BlackBerryCerticomSBGSE",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-13.1.0-48/BlackBerryCerticomSBGSE.xcframework.zip",
            checksum: "08f6d4a0607ff97f87732d1da87a1f3cf4e34c699b448f2c5abb08630d52e344"
        ),
        .binaryTarget(
            name: "BlackBerryDynamics",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-13.1.0-48/BlackBerryDynamics.xcframework.zip",
            checksum: "8d74ab2bbae407745fd2d34bef2ba44ebabdd004963e0e8d8cc8ec9361d5f992"
        ),
        .binaryTarget(
            name: "BlackBerryDynamicsAutomatedTestSupportLibrary",
            url: "https://github.com/MFB-Technologies-Inc/blackberry-dynamics-ios-sdk/releases/download/pre-13.1.0-48/BlackBerryDynamicsAutomatedTestSupportLibrary.xcframework.zip",
            checksum: "95eaca8062aa648a1d79400bce7b56b141ccaf656604b684bac2f40ba058553c"
        ),
    ]
)
