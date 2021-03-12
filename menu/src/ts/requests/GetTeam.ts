import { TeamNum } from "@utils";

export const GET_TEAM = "get_team";

export type TGetTeamInput = {
  type: "get_team";
  message?: undefined;
};

export type TGetTeamResponse = {
  type: "get_team";
  message: {
    team: TeamNum;
  };
};
