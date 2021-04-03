import { TeamNum } from "@utils";

export const GET_RADAR_DATA = "get_radar_data";

export interface IRadarData {
  name: string;
  user_id: number;
  team_num: TeamNum;
  is_fake_player: boolean;

  ping: number;
  money: number;
  kills: number;
  assists: number;
  deaths: number;
  mvps: number;
  score: number;

  competitive_ranking: number;
  competitive_wins: number;

  x: number;
  y: number;
  z: number;
}

export type TGetRadarDataResponse = {
  type: "get_radar_data";
  message: IRadarData[];
};
