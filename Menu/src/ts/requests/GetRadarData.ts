import { TeamNum } from "@utils";

export const GET_RADAR_DATA = "get_radar_data";

export interface IRadarData {
  name: string;
  userID: number;
  teamNum: TeamNum;
  isFakePlayer: boolean;

  ping: number;
  money: number;
  kills: number;
  assists: number;
  deaths: number;
  MVPs: number;
  score: number;

  competitiveRanking: number;
  competitiveWins: number;
}

export type TGetRadarDataResponse = {
  type: "get_radar_data";
  message: IRadarData[];
};
