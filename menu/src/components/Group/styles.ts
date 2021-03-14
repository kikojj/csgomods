import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export type Props = {
  width: number | string;
};
export const useStyles = makeStyles({
  container: {
    padding: "35px 0",
    width: (props: Props) => props.width,
    background: colors.teritary,
    borderRadius: 5,
  },
  label: {
    padding: "0 23px",
  },
  label_text: {
    padding: 2,

    fontWeight: 500,
    fontSize: 18,
    color: "#fff",
  },
  label_border: {
    marginTop: 15,
    height: 4,

    background: colors.blue,
    borderRadius: "2px",
  },
  content: {
    marginTop: 30,
    padding: "0 25px",
  },
});
