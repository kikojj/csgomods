import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export const useStyles = makeStyles({
  container: {
    display: "flex",
  },
  player: {
    display: "flex",
    alignItems: "center",
    justifyContent: "space-between",
  },
  player_info: {
    display: "flex",
    alignItems: "center",
  },
  player_name: {
    marginRight: 15,
    width: 110,
  },
  player_rank: {
    marginRight: 15,
    width: 34,

    "&>img": {
      display: "block",
      width: 34,
      height: 14,
    },
  },
  player_wins: {
    marginRight: 15,
    width: 45,

    display: "flex",
    alignItems: "center",

    "&>img": {
      marginRight: 5,
      display: "block",
      width: 16,
      height: 16,
    },
  },
  player_stats: {
    display: "flex",
    alignItems: "center",
  },
  player_stat: {
    marginRight: 15,
    width: 25,
  },
  player_money: {
    marginRight: 15,
    width: 60,
  },
  player_mvps: {
    marginRight: 15,
    width: 25,

    position: "relative",

    "&>img": {
      display: "block",
    },

    "&>span": {
      fontSize: 9,

      position: "absolute",
      top: -5,
      left: 12,
    },
  },
});
