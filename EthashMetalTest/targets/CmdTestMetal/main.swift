//
//  main.swift
//  CmdTestMetal
//
//  Created by Jakub Tomanik on 13/02/2019.
//  Copyright © 2019 Jakub Tomanik. All rights reserved.
//

import Foundation

let backend = EthashTests(backend: EthashGPU())
backend?.testUnits()

