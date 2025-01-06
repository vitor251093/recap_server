local L0_1, L1_1
L0_1 = require
L1_1 = "Lua!Vector.lua"
L0_1(L1_1)

function L0_1(A0_2, A1_2, A2_2, A3_2, A4_2)
  local L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2
  L5_2 = false
  L6_2 = 0
  L7_2 = 20
  L8_2 = nil
  L9_2 = nil
  L10_2 = nil
  while L6_2 < L7_2 and not L5_2 do
    L11_2 = math
    L11_2 = L11_2.random
    L11_2 = L11_2()
    L12_2 = math
    L12_2 = L12_2.pi
    L11_2 = L11_2 * L12_2
    L11_2 = L11_2 * 2
    L12_2 = A4_2.normalTeleportDistance
    L13_2 = math
    L13_2 = L13_2.cos
    L14_2 = L11_2
    L13_2 = L13_2(L14_2)
    L13_2 = L13_2 * L12_2
    L8_2 = A1_2 + L13_2
    L13_2 = math
    L13_2 = L13_2.sin
    L14_2 = L11_2
    L13_2 = L13_2(L14_2)
    L13_2 = L13_2 * L12_2
    L9_2 = A2_2 + L13_2
    L10_2 = A3_2
    L13_2 = nLocomotion
    L13_2 = L13_2.IsPositionReachable
    L14_2 = A0_2
    L15_2 = L8_2
    L16_2 = L9_2
    L17_2 = L10_2
    L13_2 = L13_2(L14_2, L15_2, L16_2, L17_2)
    L5_2 = L13_2
    if L5_2 then
      L13_2 = nVector
      L13_2 = L13_2.distance
      L14_2 = A1_2
      L15_2 = A2_2
      L16_2 = A3_2
      L17_2 = L8_2
      L18_2 = L9_2
      L19_2 = L10_2
      L13_2 = L13_2(L14_2, L15_2, L16_2, L17_2, L18_2, L19_2)
      L14_2 = A4_2.minTeleportDistance
      if L13_2 > L14_2 then
        L5_2 = true
      end
    end
    L6_2 = L6_2 + 1
  end
  L11_2 = L5_2
  L12_2 = L8_2
  L13_2 = L9_2
  L14_2 = L10_2
  return L11_2, L12_2, L13_2, L14_2
end

GetRandomReachablePosition = L0_1

function L0_1(A0_2, A1_2, A2_2, A3_2, A4_2)
  local L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2
  L5_2 = false
  L6_2 = 0
  L7_2 = 20
  L8_2 = nil
  L9_2 = nil
  L10_2 = nil
  while L6_2 < L7_2 and not L5_2 do
    L11_2 = math
    L11_2 = L11_2.random
    L11_2 = L11_2()
    L12_2 = math
    L12_2 = L12_2.pi
    L11_2 = L11_2 * L12_2
    L11_2 = L11_2 * 2
    L12_2 = A4_2.normalTeleportDistance
    L13_2 = math
    L13_2 = L13_2.cos
    L14_2 = L11_2
    L13_2 = L13_2(L14_2)
    L13_2 = L13_2 * L12_2
    L8_2 = A1_2 + L13_2
    L13_2 = math
    L13_2 = L13_2.sin
    L14_2 = L11_2
    L13_2 = L13_2(L14_2)
    L13_2 = L13_2 * L12_2
    L9_2 = A2_2 + L13_2
    L10_2 = A3_2
    L13_2 = nLocomotion
    L13_2 = L13_2.FindBallRollPosition
    L14_2 = A0_2
    L15_2 = L8_2
    L16_2 = L9_2
    L17_2 = L10_2
    L13_2, L14_2, L15_2, L16_2 = L13_2(L14_2, L15_2, L16_2, L17_2)
    L10_2 = L16_2
    L9_2 = L15_2
    L8_2 = L14_2
    L5_2 = L13_2
    if L5_2 then
      L13_2 = nVector
      L13_2 = L13_2.distance
      L14_2 = A1_2
      L15_2 = A2_2
      L16_2 = A3_2
      L17_2 = L8_2
      L18_2 = L9_2
      L19_2 = L10_2
      L13_2 = L13_2(L14_2, L15_2, L16_2, L17_2, L18_2, L19_2)
      L14_2 = A4_2.minTeleportDistance
      if L13_2 > L14_2 then
        L5_2 = true
      end
      L6_2 = L6_2 + 1
    end
  end
  L11_2 = L5_2
  L12_2 = L8_2
  L13_2 = L9_2
  L14_2 = L10_2
  return L11_2, L12_2, L13_2, L14_2
end

GetRandomBallRollPosition = L0_1

function L0_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2)
  local L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2
  L6_2 = false
  L7_2 = 0
  L8_2 = 4
  L9_2 = nil
  L10_2 = nil
  L11_2 = nil
  while L7_2 < L8_2 and not L6_2 do
    L12_2 = math
    L12_2 = L12_2.random
    L12_2 = L12_2()
    L13_2 = math
    L13_2 = L13_2.pi
    L12_2 = L12_2 * L13_2
    L12_2 = L12_2 * 2
    L13_2 = math
    L13_2 = L13_2.random
    L13_2 = L13_2()
    L14_2 = A5_2 - A4_2
    L13_2 = L13_2 * L14_2
    L13_2 = A4_2 + L13_2
    L14_2 = math
    L14_2 = L14_2.cos
    L15_2 = L12_2
    L14_2 = L14_2(L15_2)
    L14_2 = L14_2 * L13_2
    L9_2 = A1_2 + L14_2
    L14_2 = math
    L14_2 = L14_2.sin
    L15_2 = L12_2
    L14_2 = L14_2(L15_2)
    L14_2 = L14_2 * L13_2
    L10_2 = A2_2 + L14_2
    L11_2 = A3_2
    L14_2 = nLocomotion
    L14_2 = L14_2.GetClosestSpawnPosition
    L15_2 = A0_2
    L16_2 = L9_2
    L17_2 = L10_2
    L18_2 = L11_2
    L14_2, L15_2, L16_2 = L14_2(L15_2, L16_2, L17_2, L18_2)
    L11_2 = L16_2
    L10_2 = L15_2
    L9_2 = L14_2
    L14_2 = nVector
    L14_2 = L14_2.distance
    L15_2 = A1_2
    L16_2 = A2_2
    L17_2 = A3_2
    L18_2 = L9_2
    L19_2 = L10_2
    L20_2 = L11_2
    L14_2 = L14_2(L15_2, L16_2, L17_2, L18_2, L19_2, L20_2)
    if A4_2 <= L14_2 and A5_2 >= L14_2 then
      L6_2 = true
    end
    L7_2 = L7_2 + 1
  end
  L12_2 = L6_2
  L13_2 = L9_2
  L14_2 = L10_2
  L15_2 = L11_2
  return L12_2, L13_2, L14_2, L15_2
end

GetRandomSpawnPosition = L0_1

function L0_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2, A8_2, A9_2)
  local L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2, L23_2, L24_2, L25_2, L26_2
  L10_2 = false
  L11_2 = 0
  L12_2 = 4
  L13_2 = nil
  L14_2 = nil
  L15_2 = nil
  L16_2 = math
  L16_2 = L16_2.atan2
  L17_2 = A5_2
  L18_2 = A4_2
  L16_2 = L16_2(L17_2, L18_2)
  while L11_2 < L12_2 and not L10_2 do
    L17_2 = math
    L17_2 = L17_2.random
    L17_2 = L17_2()
    L17_2 = L17_2 - 0.5
    L17_2 = L17_2 * A7_2
    L17_2 = L17_2 + L16_2
    L18_2 = math
    L18_2 = L18_2.random
    L18_2 = L18_2()
    L19_2 = A9_2 - A8_2
    L18_2 = L18_2 * L19_2
    L18_2 = A8_2 + L18_2
    L19_2 = math
    L19_2 = L19_2.cos
    L20_2 = L17_2
    L19_2 = L19_2(L20_2)
    L19_2 = L19_2 * L18_2
    L13_2 = A1_2 + L19_2
    L19_2 = math
    L19_2 = L19_2.sin
    L20_2 = L17_2
    L19_2 = L19_2(L20_2)
    L19_2 = L19_2 * L18_2
    L14_2 = A2_2 + L19_2
    L15_2 = A3_2
    L19_2 = nLocomotion
    L19_2 = L19_2.GetClosestSpawnPosition
    L20_2 = A0_2
    L21_2 = L13_2
    L22_2 = L14_2
    L23_2 = L15_2
    L19_2, L20_2, L21_2 = L19_2(L20_2, L21_2, L22_2, L23_2)
    L15_2 = L21_2
    L14_2 = L20_2
    L13_2 = L19_2
    L19_2 = nVector
    L19_2 = L19_2.distance
    L20_2 = A1_2
    L21_2 = A2_2
    L22_2 = A3_2
    L23_2 = L13_2
    L24_2 = L14_2
    L25_2 = L15_2
    L19_2 = L19_2(L20_2, L21_2, L22_2, L23_2, L24_2, L25_2)
    if A8_2 <= L19_2 and A9_2 >= L19_2 then
      L20_2 = nVector
      L20_2 = L20_2.direction
      L21_2 = L13_2
      L22_2 = L14_2
      L23_2 = L15_2
      L24_2 = A1_2
      L25_2 = A2_2
      L26_2 = A3_2
      L20_2, L21_2, L22_2 = L20_2(L21_2, L22_2, L23_2, L24_2, L25_2, L26_2)
      L23_2 = math
      L23_2 = L23_2.acos
      L24_2 = L20_2 * A4_2
      L25_2 = L21_2 * A5_2
      L24_2 = L24_2 + L25_2
      L23_2 = L23_2(L24_2)
      L24_2 = A7_2 * 0.5
      if L23_2 < L24_2 then
        L10_2 = true
      end
    end
    L11_2 = L11_2 + 1
  end
  L17_2 = L10_2
  L18_2 = L13_2
  L19_2 = L14_2
  L20_2 = L15_2
  return L17_2, L18_2, L19_2, L20_2
end

GetRandomSpawnPositionInCone = L0_1

function L0_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2
  L3_2 = 0
  repeat
    L4_2 = math
    L4_2 = L4_2.random
    L4_2 = L4_2()
    L4_2 = L4_2 * 6.28
    L5_2 = math
    L5_2 = L5_2.cos
    L6_2 = L4_2
    L5_2 = L5_2(L6_2)
    L6_2 = math
    L6_2 = L6_2.sin
    L7_2 = L4_2
    L6_2 = L6_2(L7_2)
    L7_2 = nLocomotion
    L7_2 = L7_2.DistanceToObstacle
    L8_2 = A0_2
    L9_2 = L5_2
    L10_2 = L6_2
    L11_2 = 0
    L7_2 = L7_2(L8_2, L9_2, L10_2, L11_2)
    if A1_2 < L7_2 then
      if A2_2 < L7_2 then
        L7_2 = A2_2
      end
      L8_2 = math
      L8_2 = L8_2.random
      L8_2 = L8_2()
      L9_2 = L7_2 - A1_2
      L8_2 = L8_2 * L9_2
      L8_2 = A1_2 + L8_2
      L9_2 = nGameObject
      L9_2 = L9_2.GetPosition
      L10_2 = A0_2
      L9_2, L10_2, L11_2 = L9_2(L10_2)
      L12_2 = L5_2 * L8_2
      L12_2 = L9_2 + L12_2
      L13_2 = L6_2 * L8_2
      L13_2 = L10_2 + L13_2
      L14_2 = L11_2
      L15_2 = nLocomotion
      L15_2 = L15_2.GetClosestPosition
      L16_2 = A0_2
      L17_2 = L12_2
      L18_2 = L13_2
      L19_2 = L14_2
      L15_2, L16_2, L17_2 = L15_2(L16_2, L17_2, L18_2, L19_2)
      L14_2 = L17_2
      L13_2 = L16_2
      L12_2 = L15_2
      L15_2 = true
      L16_2 = L12_2
      L17_2 = L13_2
      L18_2 = L14_2
      return L15_2, L16_2, L17_2, L18_2
    end
    L3_2 = L3_2 + 1
  until 5 < L3_2
  L4_2 = false
  L5_2 = 0
  L6_2 = 0
  L7_2 = 0
  return L4_2, L5_2, L6_2, L7_2
end

GetRandomJumpPositionInRange = L0_1
