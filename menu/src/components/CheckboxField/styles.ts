import { makeStyles } from "@material-ui/styles";

export const useStyles = makeStyles({
  container: {
    width: "100%",
  },
  containerCheckbox: {
    width: "100%",
    display: "flex",
    justifyContent: "space-between",
    alignItems: "center",
  },
  label: {
    marginTop: 2,
    display: "block",

    fontWeight: 400,
    fontSize: 14,
    lineHeight: 14,

    color: "#fff",
  },
  helperText: {
    marginTop: 4,
    fontSize: 12,
    color: "rgba(255,255,255,0.6)",
  },
});
