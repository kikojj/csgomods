export const getColumnWidth = (cols: number, marginLeft: number = 100) =>
  `calc((100% - ${cols - 1}*${marginLeft}px) / ${cols})`;
