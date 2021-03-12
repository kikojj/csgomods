export const Skeleton = {
  Nearest: 0,

  Navel: 3,
  Stomach: 4,
  Chest: 6,
  Neck: 7,
  Head: 8,

  "Left shoulder": 11,
  "Left eblow": 12,
  "Left hand": 13,

  "Right shoulder": 41,
  "Right eblow": 42,
  "Right hand": 43,

  "Left thigh": 70,
  "Left knee": 71,
  "Left foot": 72,

  "Right thigh": 77,
  "Right knee": 78,
  "Right foot": 79,
};

export const bones: (keyof typeof Skeleton)[] = [
  "Nearest",
  "Navel",
  "Stomach",
  "Chest",
  "Neck",
  "Head",
  "Left shoulder",
  "Left eblow",
  "Left hand",
  "Right shoulder",
  "Right eblow",
  "Right hand",
  "Left thigh",
  "Left knee",
  "Left foot",
  "Right thigh",
  "Right knee",
  "Right foot",
];
