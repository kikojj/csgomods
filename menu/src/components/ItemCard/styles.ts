import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export const useStyles = makeStyles({
  card: {
    width: 200,
  },
  card_action: {
    height: "100%",
    display: "flex",
    flexDirection: "column",
  },
  card_media: {
    margin: 20,
    width: 160,
    height: 110,
  },
});
