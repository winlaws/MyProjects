using System;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;

namespace SCPSInventory.Models
{
    public class Asset
    {
        
        [Required]
        [RegularExpression("^[0-9]{8}$", ErrorMessage = "Cost Center ID must be an eight digit number (00000000-99999999)")]
        [Display(Name = "Asset ID")]
        public string AssetId { get; set; }
        [Display(Name = "Serial Number")]
        public string SerialNumber { get; set; }
        public string Description { get; set; }

        [Required]
        [RegularExpression("^[0-9]{4}$", ErrorMessage = "Cost Center ID must be a four digit number (0000-9999)")]
        [Display(Name = "Cost Center ID")]
        public string ccId { get; set; }
        [Required]
        public string Building { get; set; }
        [Required]
        public string Room { get; set; }
        [Display(Name = "Inventory Date")]
        public DateTime? InventoryDate { get; set; }
    }
}