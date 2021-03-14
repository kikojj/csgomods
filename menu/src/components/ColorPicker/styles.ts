import { makeStyles } from "@material-ui/styles";

import { colors } from "@utils";

import { ColorRGBA } from ".";

export type Props = {
  color: ColorRGBA;
};
export const useStyles = makeStyles({
  container: {
    position: "relative",
  },
  colorContainer: {
    width: 20,
    height: 20,

    background: (props: Props) => `rgba(${props.color.r}, ${props.color.g}, ${props.color.b}, ${props.color.a})`,
    border: `2px solid ${colors.secondary}`,
    boxSizing: "border-box",
    borderRadius: 4,

    cursor: "pointer",
  },
  pickerContainer: {
    padding: 20,
    width: 300,

    borderRadius: 5,
    backgroundColor: colors.darkBlue,

    position: "absolute",
    top: 22,
    left: 22,
    zIndex: 1,
  },
});
