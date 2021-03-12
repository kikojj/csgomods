import { makeStyles } from "@material-ui/styles";
import { colors_ as colors } from "@utils";

export type Props = { size: "small" | "large" };
export const useStyles = makeStyles({
  container: {
    display: "flex",
    flexDirection: (props: Props) => (props.size === "large" ? "column" : "row"),
    alignItems: "center",
    justifyContent: (props: Props) => (props.size === "large" ? "center" : "flex-start"),
  },
  image: {
    width: (props: Props) => (props.size === "large" ? 64 : 20),
    borderRadius: (props: Props) => (props.size === "large" ? 32 : 10),
  },
  text: {
    marginTop: (props: Props) => (props.size === "large" ? 20 : 0),
    marginLeft: (props: Props) => (props.size === "large" ? 0 : 5),

    fontWeight: 500,
    fontSize: (props: Props) => (props.size === "large" ? 24 : 14),

    color: "#fff",
  },
});
