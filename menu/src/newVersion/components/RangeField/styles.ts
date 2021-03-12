import { makeStyles } from "@material-ui/styles";
import { colors_ as colors, hexAlpha } from "@utils";

export const useStyles = makeStyles({
  container: {
    width: "100%",
  },
  label: {
    marginBottom: 8,
    fontWeight: 400,
    fontSize: 14,
    color: "#fff",
  },
  helperText: {
    marginTop: 4,
    fontSize: 12,
    color: "rgba(255,255,255,0.6)",
  },
});
