import { makeStyles } from "@material-ui/styles";
import { colors, hexAlpha } from "@utils";

export type Props = {
  color: string;
};
export const useStyles = makeStyles({
  container: {
    padding: "7px 15px",

    display: "flex",
    alignItems: "center",
    justifyContent: "center",

    borderRadius: 2,
    backgroundColor: (props: Props) => props.color,

    color: "#fff",
    fontSize: 14,

    cursor: "pointer",
  },
});
