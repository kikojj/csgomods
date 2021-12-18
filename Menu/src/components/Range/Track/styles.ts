import { makeStyles } from "@material-ui/styles";
import { colors, hexAlpha } from "@utils";

export type Props = {
  valueInPercents: number;
  color: string;
};
export const useStyles = makeStyles({
  trackBackground: {
    height: 8,
    display: "flex",
    width: "100%",
  },
  trackValue: {
    height: 8,
    width: "100%",
    borderRadius: 4,
    background: ({ color, valueInPercents }: Props) =>
      `linear-gradient(90deg, ${hexAlpha(color, 50)} 0%, ${color} ${valueInPercents}%, ${colors.gray} ${valueInPercents}%,
      ${colors.gray} 100%)`,
    alignSelf: "center",
  },
});
