local L0_1, L1_1
L0_1 = require
L1_1 = "0x3681d755!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "0x3681d755!Global.lua"
L0_1(L1_1)
L0_1 = {}
nExample = L0_1
L0_1 = nExample

function L1_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2
  L3_2 = nDebug
  L3_2 = L3_2.SetAlpha
  L4_2 = 1
  L3_2(L4_2)
  L3_2 = nDebug
  L3_2 = L3_2.SetDepthEnabled
  L4_2 = false
  L3_2(L4_2)
  L3_2 = nil
  L4_2 = nil
  L5_2 = nil
  L6_2 = nil
  L7_2 = nGameObject
  L7_2 = L7_2.GetPosition
  L8_2 = A2_2
  L7_2, L8_2, L9_2 = L7_2(L8_2)
  L5_2 = L9_2
  L4_2 = L8_2
  L3_2 = L7_2
  L7_2 = nGameObject
  L7_2 = L7_2.GetFootprintRadius
  L8_2 = A2_2
  L7_2 = L7_2(L8_2)
  L6_2 = L7_2
  L7_2 = nDebug
  L7_2 = L7_2.SetColor
  L8_2 = 1
  L9_2 = 0
  L10_2 = 0
  L7_2(L8_2, L9_2, L10_2)
  L7_2 = nDebug
  L7_2 = L7_2.DrawCircle
  L8_2 = L3_2
  L9_2 = L4_2
  L10_2 = L5_2
  L11_2 = 0
  L12_2 = 0
  L13_2 = 1
  L14_2 = L6_2
  L7_2(L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2)
  L7_2 = nGameObject
  L7_2 = L7_2.GetPosition
  L8_2 = A0_2
  L7_2, L8_2, L9_2 = L7_2(L8_2)
  L5_2 = L9_2
  L4_2 = L8_2
  L3_2 = L7_2
  L7_2 = nGameObject
  L7_2 = L7_2.GetFootprintRadius
  L8_2 = A0_2
  L7_2 = L7_2(L8_2)
  L6_2 = L7_2
  L7_2 = nDebug
  L7_2 = L7_2.SetColor
  L8_2 = 0
  L9_2 = 1
  L10_2 = 0
  L7_2(L8_2, L9_2, L10_2)
  L7_2 = nDebug
  L7_2 = L7_2.DrawCircle
  L8_2 = L3_2
  L9_2 = L4_2
  L10_2 = L5_2
  L11_2 = 0
  L12_2 = 0
  L13_2 = 1
  L14_2 = L6_2
  L7_2(L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2)
  L7_2 = nGameObject
  L7_2 = L7_2.GetPosition
  L8_2 = A1_2
  L7_2, L8_2, L9_2 = L7_2(L8_2)
  L5_2 = L9_2
  L4_2 = L8_2
  L3_2 = L7_2
  L7_2 = nGameObject
  L7_2 = L7_2.GetFootprintRadius
  L8_2 = A1_2
  L7_2 = L7_2(L8_2)
  L6_2 = L7_2
  L7_2 = nDebug
  L7_2 = L7_2.SetColor
  L8_2 = 0
  L9_2 = 0
  L10_2 = 1
  L7_2(L8_2, L9_2, L10_2)
  L7_2 = nDebug
  L7_2 = L7_2.DrawCircle
  L8_2 = L3_2
  L9_2 = L4_2
  L10_2 = L5_2
  L11_2 = 0
  L12_2 = 0
  L13_2 = 1
  L14_2 = L6_2
  L7_2(L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2)
end

L0_1.TestEventListener = L1_1
