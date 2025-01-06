local L0_1, L1_1
L0_1 = {}
nVector = L0_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2)
  local L6_2, L7_2
  L6_2 = A0_2 * A3_2
  L7_2 = A1_2 * A4_2
  L6_2 = L6_2 + L7_2
  L7_2 = A2_2 * A5_2
  L6_2 = L6_2 + L7_2
  return L6_2
end

L0_1.dot = L1_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2
  L3_2 = math
  L3_2 = L3_2.sqrt
  L4_2 = A0_2 * A0_2
  L5_2 = A1_2 * A1_2
  L4_2 = L4_2 + L5_2
  L5_2 = A2_2 * A2_2
  L4_2 = L4_2 + L5_2
  return L3_2(L4_2)
end

L0_1.len = L1_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2
  L3_2 = A0_2 * A0_2
  L4_2 = A1_2 * A1_2
  L3_2 = L3_2 + L4_2
  L4_2 = A2_2 * A2_2
  L3_2 = L3_2 + L4_2
  return L3_2
end

L0_1.sqrlen = L1_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2)
  local L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2
  L6_2 = A0_2 - A3_2
  L7_2 = A1_2 - A4_2
  L8_2 = A2_2 - A5_2
  L9_2 = nVector
  L9_2 = L9_2.len
  L10_2 = L6_2
  L11_2 = L7_2
  L12_2 = L8_2
  return L9_2(L10_2, L11_2, L12_2)
end

L0_1.distance = L1_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2)
  local L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2
  L6_2 = A0_2 - A3_2
  L7_2 = A1_2 - A4_2
  L8_2 = A2_2 - A5_2
  L9_2 = nVector
  L9_2 = L9_2.sqrlen
  L10_2 = L6_2
  L11_2 = L7_2
  L12_2 = L8_2
  return L9_2(L10_2, L11_2, L12_2)
end

L0_1.distance2 = L1_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2, L6_2, L7_2
  L3_2 = math
  L3_2 = L3_2.sqrt
  L4_2 = A0_2 * A0_2
  L5_2 = A1_2 * A1_2
  L4_2 = L4_2 + L5_2
  L5_2 = A2_2 * A2_2
  L4_2 = L4_2 + L5_2
  L4_2 = L4_2 + 1.0E-8
  L3_2 = L3_2(L4_2)
  L4_2 = 1 / L3_2
  A0_2 = A0_2 * L4_2
  A1_2 = A1_2 * L4_2
  A2_2 = A2_2 * L4_2
  L5_2 = A0_2
  L6_2 = A1_2
  L7_2 = A2_2
  return L5_2, L6_2, L7_2
end

L0_1.normalize = L1_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2)
  local L6_2, L7_2, L8_2, L9_2, L10_2, L11_2
  L6_2 = A1_2 * A5_2
  L7_2 = A2_2 * A4_2
  L6_2 = L6_2 - L7_2
  L7_2 = A2_2 * A3_2
  L8_2 = A0_2 * A5_2
  L7_2 = L7_2 - L8_2
  L8_2 = A0_2 * A4_2
  L9_2 = A1_2 * A3_2
  L8_2 = L8_2 - L9_2
  L9_2 = L6_2
  L10_2 = L7_2
  L11_2 = L8_2
  return L9_2, L10_2, L11_2
end

L0_1.cross = L1_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2)
  local L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2
  L6_2 = A0_2 - A3_2
  L7_2 = A1_2 - A4_2
  L8_2 = A2_2 - A5_2
  L9_2 = nVector
  L9_2 = L9_2.normalize
  L10_2 = L6_2
  L11_2 = L7_2
  L12_2 = L8_2
  return L9_2(L10_2, L11_2, L12_2)
end

L0_1.direction = L1_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2)
  local L7_2, L8_2, L9_2, L10_2, L11_2, L12_2
  L7_2 = A3_2 - A0_2
  L7_2 = L7_2 * A6_2
  L7_2 = L7_2 + A0_2
  L8_2 = A4_2 - A1_2
  L8_2 = L8_2 * A6_2
  L8_2 = L8_2 + A1_2
  L9_2 = A5_2 - A2_2
  L9_2 = L9_2 * A6_2
  L9_2 = L9_2 + A2_2
  L10_2 = L7_2
  L11_2 = L8_2
  L12_2 = L9_2
  return L10_2, L11_2, L12_2
end

L0_1.lerp = L1_1
L0_1 = nVector

function L1_1(A0_2, A1_2, A2_2, A3_2)
  local L4_2, L5_2, L6_2
  A0_2 = A0_2 * A3_2
  A1_2 = A1_2 * A3_2
  A2_2 = A2_2 * A3_2
  L4_2 = A0_2
  L5_2 = A1_2
  L6_2 = A2_2
  return L4_2, L5_2, L6_2
end

L0_1.scale = L1_1
